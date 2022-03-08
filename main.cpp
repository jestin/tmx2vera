#include <iostream>

#include<stdlib.h>
#include<argp.h>

#include"tilemap.h"
#include"vera_tilemap.h"

const char *argp_program_version = "tmx2vera 0.1";
const char *argp_program_bug_address = "https://github.com/jestin/tmx2vera/issues";
static char doc[] = "A tool to convert Tiled maps into files usable by the VERA chip of the Commander X16 computer";
static char args_doc[] = "TMX_FILE OUTPUT_FILE";

static struct argp_option options[] = {
	{"layer", 'l', "LAYER_NAME", 0, "The name of the layer to convert"},
	{ 0 }
};

struct arguments
{
	char *args[2];
	char *layer_name;
};

static error_t parse_opt(int key, char *arg, struct argp_state *state)
{
	struct arguments *args = (arguments*) state->input;

	switch(key)
	{
		case 'l':
			args->layer_name = arg;
			break;
		case ARGP_KEY_ARG:
			if(state->arg_num >= 2)
				argp_usage(state);
			args->args[state->arg_num] = arg;
			break;
		case ARGP_KEY_END:
			if(state->arg_num < 2)
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
	// set locale to work with Glib::ustring
	std::locale::global(std::locale(""));

	struct arguments args;
	args.layer_name = (char*) "-";

	argp_parse(&argp, argc, argv, 0, 0, &args);

	std::cout << "Generating " << args.args[1] << " from '" << args.layer_name << "' layer of " << args.args[0] << "...";


	try {
		Tilemap map(args.args[0]);
		VeraTilemap veraMap(&map);
		veraMap.writeFile(args.args[1], std::string(args.layer_name));
	}
	catch(const TilemapFileException& e)
	{
		std::cerr << "Exception caught: " << e.message << std::endl;
	}

	std::cout << "Done" << std::endl;

	return 0;
}
