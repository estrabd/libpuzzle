#include "puzzle_common.h"
#include "puzzle.h"

typedef struct Opts_ {
    const char *file1;    
    int fix_for_texts;
    int exit;
    double similarity_threshold;
} Opts;

void usage(void)
{
    puts("\nUsage: puzzle-sig <file>\n");
    exit(EXIT_SUCCESS);
}

int parse_opts(Opts * const opts, PuzzleContext * context,
               int argc, char * const *argv) {
    int opt;
    extern char *optarg;
    extern int optind;

    argv += optind;
    opts->file1 = *argv++;
    
    return 0;
}

int main(int argc, char *argv[])
{
    Opts opts;
    PuzzleContext context;
    PuzzleCvec cvec1;
    double d;
    
    puzzle_init_context(&context);    
    parse_opts(&opts, &context, argc, argv);
    puzzle_init_cvec(&context, &cvec1);
    if (puzzle_fill_cvec_from_file(&context, &cvec1, opts.file1) != 0) {    
        fprintf(stderr, "Unable to read [%s]\n", opts.file1);
        return 1;
    }

    // bde
    size_t remaining;
    int c2;
    remaining = cvec1.sizeof_vec;
    do {
        remaining--;
        c2 = (int) cvec1.vec[remaining];
        printf("%u",cvec1.vec[remaining]);
    } while (remaining > (size_t) 0U);
    printf("\n");

    puzzle_free_cvec(&context, &cvec1);
    puzzle_free_context(&context);

    return 0;
}
