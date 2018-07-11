#include <graphics/format/obj.h>
#include <utils/log.h>
#include <fstream>
using namespace oi::gc;
using namespace oi;

//This can't be handled by the FileHandler, because the FileHandler is only available runtime from an app
//The FileHandler itself is based around read and readwrite structure, which we don't care about on PC.
//FileHandler is also relative to the working directory and not absolute.
Buffer loadFileAbsolute(String path) {

	std::ifstream file(path.toCString(), std::ios::binary);

	if (!file.good()) {
		Log::error("Couldn't open that file");
		return {};
	}

	u32 length = (u32) file.rdbuf()->pubseekoff(0, std::ios_base::end);

	Buffer b = Buffer(length);
	file.seekg(0, std::ios::beg);
	file.read((char*)b.addr(), b.size());
	file.close();

	return b;

}

//This can't be handled by the FileHandler, because the FileHandler is only available runtime from an app
//The FileHandler itself is based around read and readwrite structure, which we don't care about on PC.
//FileHandler is also relative to the working directory and not absolute.
bool writeFileAbsolute(String path, Buffer buffer) {

	std::ofstream file(path.toCString(), std::ios::binary);

	if (!file.good())
		return Log::error("Couldn't open that file (for write)");

	file.write((char*)buffer.addr(), buffer.size());
	file.close();

	return true;
}

//This project is the conversion from obj/fbx to oiRM file format.
//It is written for desktop only; since those are the ones building the projects.
//In an Android App, you're not able to write into resources, so all of that should be handled beforehand.
int main(int argv, char *argc[]) {

	if (argv != 2)
		return (int) Log::error("Syntax: oirm_gen.exe \"modelPath\"");

	String path = argc[1];

	bool isValid = path.endsWithIgnoreCase(".obj") || path.endsWithIgnoreCase(".fbx");

	if(!isValid)
		return (int) Log::error(String("Syntax: oirm_gen.exe \"modelPath\"; \"") + path + "\" is not a valid model path");

	Buffer buf = loadFileAbsolute(path);

	if(buf.size() == 0)
		return (int) Log::error(String("Couldn't load \"") + path + "\"");

	std::vector<u32> loc = path.find('.');
	String base = path.cutEnd(loc[loc.size() - 1]);

	int res = 1;

	if (path.endsWithIgnoreCase(".obj")) {

		Buffer model = Obj::convert(buf);

		if (model.size() == 0)
			res = (int) Log::error(String("Couldn't convert \"") + path + "\"");
		else {
			res = (int) writeFileAbsolute(base + ".oiRM", model);
			model.deconstruct();
		}

	} else if(path.endsWithIgnoreCase(".fbx"))
		res = (int)Log::error(String("Fbx format conversion isn't supported yet... Skipping \"") + path + "\"");

	buf.deconstruct();
	
	if(res == 1)
		Log::println(String("Successfully converted \"") + path + "\" to \"" + base + ".oiRM\"");

	return res;
}