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

int parse_opts(Opts * const opts, int argc, char * const *argv) {
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
    parse_opts(&opts, argc, argv);
    return _puzzle_fill_cvec_from_file(opts.file1);
}

int _puzzle_fill_cvec_from_file(char *filename) {
    PuzzleContext context;
    PuzzleCvec cvec1;
    PuzzleCompressedCvec c_cvec1;
    double d;
    
    puzzle_init_context(&context);    
    puzzle_init_cvec(&context, &cvec1);

    // update lambda (number of samples) taken for each image to 13
    puzzle_set_lambdas(&context, 13);

    // set p-ratio (using default/reference of 2.0), but lower if too many false positives
    puzzle_set_p_ratio(&context, 2.0);

    if (puzzle_fill_cvec_from_file(&context, &cvec1, filename) != 0) {    
        fprintf(stderr, "Unable to read [%s]\n", filename);
        return 1;
    }

    // compress
    puzzle_init_compressed_cvec(&context, &c_cvec1);
    puzzle_compress_cvec(&context, &c_cvec1, &cvec1);

    // bde - just prints the signature
    size_t remaining;
    int c2;
    remaining = c_cvec1.sizeof_compressed_vec;
    do {
        remaining--;
        c2 = (int) c_cvec1.vec[remaining];
        printf("%u",c_cvec1.vec[remaining]);
    } while (remaining > (size_t) 0U);
    printf("\n");

    puzzle_free_compressed_cvec(&context, &c_cvec1);
    puzzle_free_cvec(&context, &cvec1);
    puzzle_free_context(&context);

    return 0;
}
