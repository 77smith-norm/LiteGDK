#include <catch2/catch_test_macros.hpp>

#include <filesystem>

#include "DarkGDK.h"
#include "helpers/RuntimeTestContext.h"

namespace {
std::string fixtureImagePath() {
    return (std::filesystem::current_path().parent_path() / "tests/fixtures/assets/test_image.ppm").string();
}

void loadFixtureImage(litegdk::tests::RuntimeTestContext& context, int imageId) {
    const auto fixturePath = fixtureImagePath();
    context.backend().configuredImages.insert_or_assign(fixturePath, litegdk::ImageLoadResult{
        .width = 2,
        .height = 1,
    });
    dbLoadImage(fixturePath.c_str(), imageId);
}
}  // namespace

TEST_CASE("dbSprite creates visible sprite state from a loaded image", "[sprites]") {
    litegdk::tests::RuntimeTestContext context;
    loadFixtureImage(context, 1);

    dbSprite(4, 12, 18, 1);

    REQUIRE(dbSpriteExist(4) == TRUE);

    const auto* sprite = context.app().sprites().find(4);
    REQUIRE(sprite != nullptr);
    REQUIRE(sprite->imageId == 1);
    REQUIRE(sprite->x == 12.0f);
    REQUIRE(sprite->y == 18.0f);
    REQUIRE(sprite->visible);
}

TEST_CASE("sprite position and visibility helpers mutate stored sprite state", "[sprites]") {
    litegdk::tests::RuntimeTestContext context;
    loadFixtureImage(context, 2);
    dbSprite(6, 30, 40, 2);

    dbHideSprite(6);
    REQUIRE_FALSE(context.app().sprites().find(6)->visible);

    dbShowSprite(6);
    dbXSprite(6, 90);
    dbYSprite(6, 120);

    const auto* sprite = context.app().sprites().find(6);
    REQUIRE(sprite != nullptr);
    REQUIRE(sprite->visible);
    REQUIRE(sprite->x == 90.0f);
    REQUIRE(sprite->y == 120.0f);

    dbDeleteSprite(6);
    REQUIRE(dbSpriteExist(6) == FALSE);
}

TEST_CASE("dbSprite records diagnostics when the image slot is missing", "[sprites]") {
    litegdk::tests::RuntimeTestContext context;

    dbSprite(2, 0, 0, 99);

    REQUIRE(dbSpriteExist(2) == FALSE);
    REQUIRE(context.app().diagnostics().count() == 1);

    const auto& warning = context.app().diagnostics().warnings().front();
    REQUIRE(warning.command == "dbSprite");
    REQUIRE(warning.code == litegdk::CompatibilityCode::failedPrecondition);
}
