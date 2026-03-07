#pragma once

namespace litegdk {
    class Runtime {
    public:
        Runtime();
        ~Runtime();

        void initialize();
        void shutdown();
        bool isRunning() const;
    };

    Runtime& runtime();
}
