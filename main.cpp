#include <iostream>

#include<stdlib.h>
#include<argp.h>

#include"tilemap.h"
#include"vera_tilemap.h"

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

		int index = 0;
		for(const auto &item : map.Layers())
		{
			std::cout << index++ << ":  " << item.first << std::endl;
			Layer *layer = item.second;
			std::cout << "Layer ID: " << layer->Id() << std::endl;
			std::cout << "Layer Name: " << layer->Name() << std::endl;
			std::cout << "Layer Width: " << layer->Width() << std::endl;
			std::cout << "Layer Height: " << layer->Height() << std::endl;
		}

		std::map<std::string, Layer*> layers = map.Layers();

		Layer *namedLayer = map.Layers()[std::string(args.layer_name)];

		if(namedLayer)
		{
			VeraTilemap veraMap(namedLayer);
			veraMap.writeFile(args.args[1]);
		}

	}
	catch(const TilemapFileException& e)
	{
		std::cerr << "Exception caught: " << e.message << std::endl;
	}

	return 0;
}
