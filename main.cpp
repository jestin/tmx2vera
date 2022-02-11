#include <iostream>

#include<stdlib.h>
#include<argp.h>

#include"tilemap.h"

const char *argp_program_version = "tmx2vera 0.1";
const char *argp_program_bug_address = "<jestin.stoffel@gmail.com>";
static char doc[] = "A tool to convert Tiled maps into files usable by the VERA chip of the Commander X16 computer";
static char args_doc[] = "TMX_FILE";

static struct argp_option options[] = {
	{"verbose", 'v', 0, 0, "Produce verbose output"},
	{"quiet", 'q', 0, 0, "Don't produce any output"},
	{"silent", 's', 0, OPTION_ALIAS},
	{"output", 'o', "FILE", 0, "Output to a FILE instead of standard output"},
	{"layer", 'l', "LAYER_NAME", 0, "The name of the layer to convert"},
	{ 0 }
};

struct arguments
{
	char *args[1];
	int silent;
	int verbose;
	char *output_file;
	char *layer_name;
};

static error_t parse_opt(int key, char *arg, struct argp_state *state)
{
	struct arguments *args = (arguments*) state->input;

	switch(key)
	{
		case 'q':
		case 's':
			args->silent = 1;
			break;
		case 'v':
			args->verbose = 1;
			break;
		case 'o':
			args->output_file = arg;
			break;
		case 'l':
			args->layer_name = arg;
			break;
		case ARGP_KEY_ARG:
			if(state->arg_num >= 1)
				argp_usage(state);
			args->args[state->arg_num] = arg;
			break;
		case ARGP_KEY_END:
			if(state->arg_num < 1)
				argp_usage(state);
			break;
		default:
			return ARGP_ERR_UNKNOWN;
	}

	return 0;
}

static struct argp argp = { options, parse_opt, args_doc, doc };

int main(int argc, char **argv)
{
	struct arguments args;
	args.silent = 0;
	args.verbose = 0;
	args.output_file = (char*) "-";
	args.layer_name = (char*) "-";

	argp_parse(&argp, argc, argv, 0, 0, &args);

	std::cout << "TMX_FILE = " << args.args[0] << std::endl;
	std::cout << "OUTPUT_FILE = " << args.output_file << std::endl;
	std::cout << "LAYER_NAME = " << args.layer_name << std::endl;
	std::cout << "VERBOSE = " << (args.verbose ? "yes" : "no") << std::endl;
	std::cout << "SILENT = " << (args.silent ? "yes" : "no") << std::endl;

	try {
		Tilemap map(args.args[0]);
	}
	catch(const std::exception& e)
	{
		std::cerr << "Exception caught: " << e.what() << std::endl;
	}

	return 0;
}
