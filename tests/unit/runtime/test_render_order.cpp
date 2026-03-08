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

TEST_CASE("dbSync submits sprites before text with deterministic ordering", "[runtime][render]") {
    litegdk::tests::RuntimeTestContext context;
    loadFixtureImage(context, 1);
    loadFixtureImage(context, 2);

    dbSprite(5, 50, 50, 1);
    dbSprite(2, 20, 20, 2);
    dbText(10, 10, "first");
    dbText(30, 30, "second");

    dbSync();

    const auto& sequence = context.backend().drawCallSequence;
    REQUIRE(sequence.size() == 4);
    REQUIRE(sequence[0].label == "sprite:2");
    REQUIRE(sequence[1].label == "sprite:5");
    REQUIRE(sequence[2].label == "text:first");
    REQUIRE(sequence[3].label == "text:second");
}
