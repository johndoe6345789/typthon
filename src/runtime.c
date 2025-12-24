#include "typthon/runtime.h"
#include "typthon/version.h"

const char *typthon_version(void) {
    return TYPTHON_VERSION;
}

void typthon_print_banner(FILE *output) {
    if (output == NULL) {
        return;
    }

    fprintf(output, "Typthon %s\n", typthon_version());
}
