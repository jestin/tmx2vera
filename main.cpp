#include <iostream>

#include<stdlib.h>
#include<argp.h>

#include"tilemap.h"

const char *argp_program_version = "tmx2vera 0.1";
const char *argp_program_bug_address = "<jestin.stoffel@gmail.com>";
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

	std::cout << "TMX_FILE = " << args.args[0] << std::endl;
	std::cout << "LAYER_NAME = " << args.layer_name << std::endl;

	try {
		Tilemap map(args.args[0]);
		std::cout << "map version: " << map.MapVersion() << std::endl;
		std::cout << "tiled version: " << map.MapVersion() << std::endl;
		std::cout << "width: " << map.Width() << std::endl;
		std::cout << "height: " << map.Height() << std::endl;

		for(auto it = map.Layers().begin(); it != map.Layers().end(); ++it)
		{
			std::cout << "Layer ID: " << (*it)->Id() << std::endl;
			std::cout << "Layer Name: " << (*it)->Name() << std::endl;
			std::cout << "Layer Width: " << (*it)->Width() << std::endl;
			std::cout << "Layer Height: " << (*it)->Height() << std::endl;

			for(int y = 0; y < (*it)->Height(); y++)
			{
				for(int x = 0; x < (*it)->Width(); x++)
				{
					std::cout << (*it)->Data()[(y * (*it)->Width()) + x] << ",";
				}
				std::cout << std::endl;
			}
		}
	}
	catch(const TilemapFileException& e)
	{
		std::cerr << "Exception caught: " << e.message << std::endl;
	}

	return 0;
}
