#include <iostream>

#include<stdlib.h>
#include<argp.h>

#include"tilemap.h"
#include"output_tilemap.h"
#include"vera_tilemap.h"
#include"collision_tilemap.h"

const char *argp_program_version = "tmx2vera 0.1";
const char *argp_program_bug_address = "https://github.com/jestin/tmx2vera/issues";
static char doc[] = "A tool to convert Tiled maps into files usable by the VERA chip of the Commander X16 computer";
static char args_doc[] = "TMX_FILE OUTPUT_FILE";

static struct argp_option options[] = {
	{"layer", 'l', "LAYER_NAME", 0, "The name of the layer to convert"},
	{"collision", 'c', 0, 0, "Output a 1 byte per tile collision map instead of 2 byte per tile VERA tile map"},
	{"disable-paloffset", 'd', 0, 0, "Do not write a palette offset to the tile data"},
	{ 0 }
};

struct arguments
{
	char *args[2];
	char *layer_name;
	int collision = 0;
	int disable_paloffset = 0;
};

static error_t parse_opt(int key, char *arg, struct argp_state *state)
{
	struct arguments *args = (arguments*) state->input;

	switch(key)
	{
		case 'l':
			args->layer_name = arg;
			break;
		case 'c':
			args->collision = 1;
			break;
		case 'd':
			args->disable_paloffset = 1;
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

	OutputTilemap *outputMap;

	try {
		Tilemap map(args.args[0]);

		if(args.collision)
		{
			outputMap = new CollisionTilemap(&map);
		}
		else
		{
			outputMap = new VeraTilemap(&map);
		}

		outputMap->writeFile(args.args[1], std::string(args.layer_name), args.disable_paloffset);

		delete outputMap;
	}
	catch(const TilemapException& e)
	{
		std::cerr << "Exception caught: " << e.message << std::endl;

		if(outputMap) {
			delete outputMap;
		}
	}

	std::cout << "Done" << std::endl;

	return 0;
}
