#include "renderer.hpp"

namespace gal::vulkan
{
	renderer::renderer(__win::impl &win, const vk::raii::PhysicalDevice &phy, instance &inst) noexcept
		: surf{inst.create_surface(win)},
			dev{phy, inst, *surf},
			swpchain{phy, dev, *surf, 800, 600},
			rndrpass{dev.create_render_pass(
				swpchain.format(),
				device::find_depth_format(phy),
				vk::SampleCountFlagBits::e1
			)}
	{
	}

	renderer::~renderer() noexcept
	{
		rndrpass.reset();
		swpchain.reset();
		surf.reset();
		dev.reset();
	}
}
