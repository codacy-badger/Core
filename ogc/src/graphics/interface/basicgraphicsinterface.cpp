#include "window/window.h"
#include "graphics/interface/basicgraphicsinterface.h"
#include "graphics/objects/render/commandlist.h"
#include "graphics/objects/shader/pipelinestate.h"
#include "graphics/objects/texture/sampler.h"
#include "graphics/objects/view/viewbuffer.h"
using namespace oi::gc;
using namespace oi;

BasicGraphicsInterface::~BasicGraphicsInterface() {
	g.destroy(view);
	g.destroy(cameraFrustum);
	g.destroy(camera);
	g.destroy(views);
	g.destroy(sampler);
	g.destroy(pipelineState);
	g.destroy(cmdList);
}

void BasicGraphicsInterface::initScene() {

	//Command list
	cmdList = g.create("Default command list", CommandListInfo());
	g.use(cmdList);

	//Setup our pipeline state (with default settings)
	PipelineStateInfo psi;
	psi.lineWidth = 3.f;
	pipelineState = g.create("Default pipeline state", psi);
	g.use(pipelineState);

	//Allocate sampler
	sampler = g.create("Default sampler", SamplerInfo(SamplerMin::Linear, SamplerMag::Linear, SamplerWrapping::Repeat));
	g.use(sampler);

	//Setup our view buffer
	views = g.create("Default view buffer", ViewBufferInfo());
	g.use(views);

	//Setup our camera
	camera = g.create("Default camera", CameraInfo(views, Vec3(3, 3, 3), Vec4(0, 0, 0, 1)));
	g.use(camera);

	//Setup our viewport
	cameraFrustum = g.create("Default viewport", CameraFrustumInfo(views, Vec2u(1, 1), 1.f, 40.f, 0.1f, 100.f));
	g.use(cameraFrustum);

	//Setup our view
	view = g.create("Default view", ViewInfo(views, camera, cameraFrustum));
	g.use(view);

}

void BasicGraphicsInterface::onAspectChange(float asp) {
	cameraFrustum->resize(getParent()->getInfo().getSize(), asp);
}