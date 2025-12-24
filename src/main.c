#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "typthon/runtime.h"
#include "typthon/version.h"

static void print_usage(void) {
    printf("Typthon %s\n", typthon_version());
    printf("usage: typthon [--version] [--help]\n");
    printf("This is a lightweight bootstrap for the Typthon runtime.\n");
}

int main(int argc, char **argv) {
    bool show_help = false;
    bool show_version = false;

    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "-h") == 0) {
            show_help = true;
        } else if (strcmp(argv[i], "--version") == 0 || strcmp(argv[i], "-V") == 0) {
            show_version = true;
        } else {
            fprintf(stderr, "unknown option: %s\n", argv[i]);
            return 1;
        }
    }

    if (show_help) {
        print_usage();
        return 0;
    }

    if (show_version || argc == 1) {
        typthon_print_banner(stdout);
        return 0;
    }

    return 0;
}
