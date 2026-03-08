#include <filesystem>
#include <iostream>

#include "DarkGDK.h"
#include "helpers/TestBackend.h"
#include "runtime/AppRuntime.h"

namespace {
std::string fixtureImagePath() {
    return (std::filesystem::current_path().parent_path() / "tests/fixtures/assets/test_image.ppm").string();
}
}  // namespace

int main() {
    auto& app = litegdk::runtime();
    auto* backend = litegdk::tests::installTestBackend(app);
    const auto fixturePath = fixtureImagePath();

    backend->configuredImages.insert_or_assign(fixturePath, litegdk::ImageLoadResult{
        .width = 2,
        .height = 1,
    });

    dbLoadImage(fixturePath.c_str(), 1);
    dbLoadImage(fixturePath.c_str(), 2);
    dbSprite(5, 50, 50, 1);
    dbSprite(2, 20, 20, 2);
    dbText(10, 10, "first");
    dbText(30, 30, "second");
    dbSync();

    std::cout << "Order=";
    for (std::size_t i = 0; i < backend->drawCallSequence.size(); ++i) {
        if (i > 0) {
            std::cout << ",";
        }

        std::cout << backend->drawCallSequence[i].label;
    }

    std::cout << "\n";
    return 0;
}
