#include <catch2/catch_test_macros.hpp>

#include <filesystem>

#include "DarkGDK.h"
#include "helpers/RuntimeTestContext.h"

namespace {
std::string fixtureImagePath() {
    return (std::filesystem::current_path().parent_path() / "tests/fixtures/assets/test_image.ppm").string();
}
}  // namespace

TEST_CASE("dbLoadImage stores fixture metadata and exposes image queries", "[images]") {
    litegdk::tests::RuntimeTestContext context;
    const auto fixturePath = fixtureImagePath();

    context.backend().configuredImages.insert_or_assign(fixturePath, litegdk::ImageLoadResult{
        .width = 2,
        .height = 1,
    });

    dbLoadImage(fixturePath.c_str(), 7);

    REQUIRE(dbImageExist(7) == TRUE);
    REQUIRE(dbGetImageWidth(7) == 2);
    REQUIRE(dbGetImageHeight(7) == 1);

    const auto* image = context.app().images().find(7);
    REQUIRE(image != nullptr);
    REQUIRE(image->sourcePath == fixturePath);
    REQUIRE(image->width == 2);
    REQUIRE(image->height == 1);
}

TEST_CASE("dbLoadImage records diagnostics for missing image files", "[images]") {
    litegdk::tests::RuntimeTestContext context;
    const auto missingPath = (std::filesystem::current_path().parent_path() / "tests/fixtures/assets/missing_image.ppm").string();

    dbLoadImage(missingPath.c_str(), 4);

    REQUIRE(dbImageExist(4) == FALSE);
    REQUIRE(dbGetImageWidth(4) == 0);
    REQUIRE(dbGetImageHeight(4) == 0);
    REQUIRE(context.app().diagnostics().count() == 1);

    const auto& warning = context.app().diagnostics().warnings().front();
    REQUIRE(warning.command == "dbLoadImage");
    REQUIRE(warning.code == litegdk::CompatibilityCode::failedPrecondition);
    REQUIRE(warning.detail.find("Image file not found:") != std::string::npos);
}

TEST_CASE("dbLoadImage rejects invalid image handles", "[images]") {
    litegdk::tests::RuntimeTestContext context;
    const auto fixturePath = fixtureImagePath();

    dbLoadImage(fixturePath.c_str(), 0);

    REQUIRE(dbImageExist(0) == FALSE);
    REQUIRE(context.app().diagnostics().count() == 1);
    REQUIRE(context.app().diagnostics().warnings().front().code == litegdk::CompatibilityCode::invalidSlotUsage);
}
