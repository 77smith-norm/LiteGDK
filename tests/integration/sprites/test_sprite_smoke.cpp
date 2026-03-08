#include <filesystem>
#include <iostream>

#include "DarkGDK.h"
#include "helpers/TestBackend.h"
#include "runtime/AppRuntime.h"

int main() {
    auto& app = litegdk::runtime();
    auto* backend = litegdk::tests::installTestBackend(app);
    const auto fixturePath = (std::filesystem::current_path().parent_path() / "tests/fixtures/assets/test_image.ppm").string();

    backend->configuredImages.insert_or_assign(fixturePath, litegdk::ImageLoadResult{
        .width = 2,
        .height = 1,
    });

    dbLoadImage(fixturePath.c_str(), 1);
    dbSprite(5, 14, 22, 1);
    dbSync();

    const auto& draw = backend->spriteDraws.front();
    std::cout << "Sprite draws=" << backend->spriteDraws.size()
              << " image=" << draw.imageId
              << " x=" << static_cast<int>(draw.x)
              << " y=" << static_cast<int>(draw.y) << "\n";
    return 0;
}
