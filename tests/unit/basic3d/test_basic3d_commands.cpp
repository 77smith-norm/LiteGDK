#include <catch2/catch_test_macros.hpp>

#include "DarkGDK.h"
#include "helpers/RuntimeTestContext.h"

TEST_CASE("basic 3D object commands create and mutate cube state", "[basic3d][commands]") {
    litegdk::tests::RuntimeTestContext context;

    dbMakeObjectCube(4, 12.0f);

    const auto* created = context.app().objects().find(4);
    REQUIRE(created != nullptr);
    REQUIRE(created->primitiveType == litegdk::PrimitiveType::cube);
    REQUIRE(created->dimensions.x == 12.0f);
    REQUIRE(created->dimensions.y == 12.0f);
    REQUIRE(created->dimensions.z == 12.0f);
    REQUIRE(created->position.x == 0.0f);
    REQUIRE(created->rotation.y == 0.0f);

    dbPositionObject(4, 3.0f, 4.0f, 5.0f);
    dbRotateObject(4, 10.0f, 20.0f, 30.0f);

    const auto* object = context.app().objects().find(4);
    REQUIRE(object != nullptr);
    REQUIRE(object->position.x == 3.0f);
    REQUIRE(object->position.y == 4.0f);
    REQUIRE(object->position.z == 5.0f);
    REQUIRE(object->rotation.x == 10.0f);
    REQUIRE(object->rotation.y == 20.0f);
    REQUIRE(object->rotation.z == 30.0f);
}

TEST_CASE("camera commands update state and dbSync submits 3D primitives", "[basic3d][commands]") {
    litegdk::tests::RuntimeTestContext context;

    dbMakeObjectCube(7, 6.0f);
    dbPositionObject(7, 3.0f, 4.0f, 5.0f);
    dbRotateObject(7, 0.0f, 45.0f, 0.0f);
    dbPositionCamera(0.0f, 2.0f, -20.0f);
    dbPointCamera(1.0f, 0.0f, 0.0f);

    dbSync();

    REQUIRE(context.backend().begin3DCount == 1);
    REQUIRE(context.backend().end3DCount == 1);
    REQUIRE(context.backend().objectDraws.size() == 1);
    REQUIRE(context.backend().lastCamera3D.has_value());

    const auto& draw = context.backend().objectDraws.front();
    REQUIRE(draw.objectId == 7);
    REQUIRE(draw.primitiveType == litegdk::PrimitiveType::cube);
    REQUIRE(draw.dimensions.x == 6.0f);
    REQUIRE(draw.position.x == 3.0f);
    REQUIRE(draw.position.y == 4.0f);
    REQUIRE(draw.position.z == 5.0f);
    REQUIRE(draw.rotation.y == 45.0f);

    const auto& camera = context.backend().lastCamera3D.value();
    REQUIRE(camera.position.x == 0.0f);
    REQUIRE(camera.position.y == 2.0f);
    REQUIRE(camera.position.z == -20.0f);
    REQUIRE(camera.target.x == 1.0f);
    REQUIRE(camera.target.y == 0.0f);
    REQUIRE(camera.target.z == 0.0f);
    REQUIRE(camera.projectionMode == litegdk::ProjectionMode::perspective);
}

TEST_CASE("basic 3D commands record diagnostics for invalid handles and missing objects", "[basic3d][commands]") {
    litegdk::tests::RuntimeTestContext context;

    dbMakeObjectCube(0, 5.0f);
    dbPositionObject(99, 1.0f, 2.0f, 3.0f);
    dbRotateObject(99, 1.0f, 2.0f, 3.0f);

    REQUIRE(context.app().diagnostics().count() == 3);

    const auto& warnings = context.app().diagnostics().warnings();
    REQUIRE(warnings[0].command == "dbMakeObjectCube");
    REQUIRE(warnings[0].code == litegdk::CompatibilityCode::invalidSlotUsage);
    REQUIRE(warnings[1].command == "dbPositionObject");
    REQUIRE(warnings[1].code == litegdk::CompatibilityCode::failedPrecondition);
    REQUIRE(warnings[2].command == "dbRotateObject");
    REQUIRE(warnings[2].code == litegdk::CompatibilityCode::failedPrecondition);
}
