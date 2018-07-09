#include "graphics/drawlist.h"
#include "graphics/gbuffer.h"
#include "graphics/graphics.h"
#include "graphics/mesh.h"
using namespace oi::gc;
using namespace oi;

const DrawListInfo DrawList::getInfo() { return info; }
u32 DrawList::getBatches() { return (u32) info.objects.size(); }
u32 DrawList::getMaxBatches() { return (u32) info.maxBatches; }
GBuffer *DrawList::getBuffer() { return info.drawBuffer; }

void DrawList::flush() {

	prepareDrawList();

	u32 totalSize = 0;

	for (auto it : info.objects)
		totalSize += it.second.objectBuffer.size();

	Buffer total(totalSize);
	totalSize = 0;

	for (auto it : info.objects) {
		total.copy(it.second.objectBuffer, it.second.objectBuffer.size(), 0, totalSize);
		totalSize += it.second.objectBuffer.size();
	}

	info.objectBuffer->set(total);

	if (info.clearOnUse)
		clear();
}

void DrawList::clear() {
	info.objects.clear();
}

void DrawList::draw(Mesh *m, u32 instances, Buffer buffer) {

	if (m->getInfo().buffer != info.meshBuffer) {
		Log::error("Every MeshBuffer requires a different DrawList. The drawcall mentioned a Mesh that wasn't in the same MeshBuffer.");
		return;
	}

	auto it = info.objects.find(m);

	if (it == info.objects.end()) {

		if (getBatches() == getMaxBatches()) {
			Log::error("The batches exceeded the maximum amount. Please increase this or decrease draw calls.");
			return;
		}

		info.objects[m] = { Buffer(buffer.addr(), buffer.size()), instances };
	}
	else {
		info.objects[m].instances += instances;
		info.objects[m].objectBuffer += buffer;
	}

}

DrawList::DrawList(DrawListInfo info) : info(info) {}

DrawList::~DrawList() { 
	g->destroy(info.drawBuffer);
}

bool DrawList::init() {

	if (info.maxBatches == 0)
		return Log::error("Couldn't create DrawList; it needs at least 1 object");

	if (info.objectBuffer == nullptr || info.meshBuffer == nullptr)
		return Log::error("Couldn't create DrawList; object buffer or mesh buffer was invalid");

	info.objects.reserve(info.maxBatches);

	if (!createCBO())
		return Log::error("Couldn't reserve draw list");

	return true;
}