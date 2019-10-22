/*
The XSM simulator starts here.
*/


#include "simulator.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static const int XSM_TIMER_DURATION = XSM_SIMULATOR_DEFTIMER;
static const int XSM_DISK_DURATION = XSM_SIMULATOR_DEFDISK;
static const int XSM_CONSOLE_DURATION = XSM_SIMULATOR_DEFCONSOLE;

/* Start the XSM machine */
int simulator_run()
{
    // Ready
    if(disk_init(_options_disk_file) != XSM_SUCCESS) {
        printf("Could not initialize disk.\n");
        printf("If you are following eXpOS roadmap, make sure your working directory\n"
               "is myexpos/xsm, so that the file %s is accessible\n", _options_disk_file);
        printf("Or manually specify the file using --disk-file /path/to/disk.xfs\n");
        return XSM_FAILURE;
    }

    // Set
    if (!machine_init(&_options))
        return XSM_FAILURE;

    // Go
    if (!machine_run())
        return XSM_FAILURE;

    printf("Machine is halting.\n");

    // Finish
    machine_destroy();
    disk_close(_options_disk_file);
    return XSM_SUCCESS;
}

/* Parse the parameters */
int simulator_parse_args(int argc, char **argv)
{
    int val;

    argv++;
    argc--;

    _options.timer = XSM_TIMER_DURATION;
    _options.console = XSM_CONSOLE_DURATION;
    _options.disk = XSM_DISK_DURATION;
    _options.stdin = stdin;
    _options_disk_file = XSM_DEFAULT_DISK;

    while (argc > 0)
    {
        if (!strcmp(*argv, "--debug"))
        {
            _options.debug = TRUE;

            argv++;
            argc--;
        }
        else if (!strcmp(*argv, "--timer"))
        {
            argv++;
            argc--;

            val = atoi(*argv);
            if (val < 0 || val > 1024)
            {
                printf("--timer takes value in the range 0-1024\n");
                exit(0);
            }
            _options.timer = val + 1;
            if (val == 0)
                _options.timer = 0;

            argv++;
            argc--;
        }
        else if (!strcmp(*argv, "--console"))
        {
            argv++;
            argc--;

            val = atoi(*argv);
            if (val < 20 || val > 1024)
            {
                printf("--console takes value in the range 20-1024\n");
                exit(0);
            }
            _options.console = val + 1;

            argv++;
            argc--;
        }
        else if (!strcmp(*argv, "--disk"))
        {
            argv++;
            argc--;

            val = atoi(*argv);
            if (val < 20 || val > 1024)
            {
                printf("--disk takes value in the range 20-1024\n");
                exit(0);
            }
            _options.disk = val + 1;

            argv++;
            argc--;
        }
        else if (!strcmp(*argv, "--disk-file"))
        {
            argv++;
            argc--;

            FILE* f = fopen(*argv, "r");
            if (f == NULL)
            {
                printf("Specified disk file can not be opened\n");
                exit(0);
            }
            fclose(f);
            _options_disk_file = *argv;

            argv++;
            argc--;
        }
        else if (!strcmp(*argv, "--stdin-file"))
        {
            argv++;
            argc--;

            FILE* f = fopen(*argv, "r");
            if (f == NULL)
            {
                printf("Specified stdin file can not be opened\n");
                exit(0);
            }
            _options.stdin = f;

            argv++;
            argc--;
        }
        else
        {
            // Unrecognised option.
            return XSM_FAILURE;
        }
    }

    return XSM_SUCCESS;
}
