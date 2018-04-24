#pragma once

#include "graphics.h"
#include "graphics/graphicsobject.h"

namespace oi {

	namespace gc {

		struct PipelineStateInfo {

			TopologyMode topologyMode;
			FillMode fillMode;
			f32 lineWidth = 1.f;
			CullMode cullMode = CullMode::Back;
			WindMode windMode = WindMode::CW;
			u32 samples = 1U;
			BlendMode blendMode = BlendMode::Alpha;
			DepthMode depthMode;

			PipelineStateInfo(TopologyMode topologyMode = TopologyMode::Triangle, FillMode fillMode = FillMode::Fill, DepthMode depthMode = DepthMode::All) : topologyMode(topologyMode), fillMode(fillMode), depthMode(depthMode) {}

		};

		class PipelineState : public GraphicsObject {

			friend class Graphics;

		public:

			PipelineStateExt &getExtension();
			
		protected:

			~PipelineState();
			PipelineState(PipelineStateInfo info);
			bool init();

		private:

			PipelineStateInfo info;
			PipelineStateExt ext;

		};

	}

}