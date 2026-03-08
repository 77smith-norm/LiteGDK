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

    dbLoadImage(fixturePath.c_str(), 3);

    std::cout << "Image exists=" << dbImageExist(3)
              << " width=" << dbGetImageWidth(3)
              << " height=" << dbGetImageHeight(3) << "\n";
    return 0;
}
