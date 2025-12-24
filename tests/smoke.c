#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "typthon/runtime.h"
#include "typthon/version.h"

int main(void) {
    const char *version = typthon_version();
    assert(version != NULL);
    assert(strlen(version) > 0);

    printf("Typthon runtime version: %s\n", version);
    typthon_print_banner(stdout);
    return 0;
}
