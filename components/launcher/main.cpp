#include <ctl/version>
#include <osal/main.hpp>
#include <ctl/string_view>
#include <gal/window.hpp>
#include <gal/gal.hpp>
#include <gal/font.hpp>
#include <osal/terminal.hpp>

#include <gamemode_client.h>

int application_main([[maybe_unused]] int argc, [[maybe_unused]] char *argv[], [[maybe_unused]] char *enp[])
{
	using namespace std::literals::string_view_literals;

	//gamemode_request_start();

	gal::software_list softinfo;
	softinfo.engine.name = "untitled engine"sv;
	softinfo.engine.version.set(gal::version_t::triplet, 0, 0, 0);
	softinfo.app.name = "untitled application"sv;
	softinfo.app.version.set(gal::version_t::triplet, 0, 0, 0);

	gal::gpu_list gpu_list{gal::collect_gpus()};

	osal::this_terminal::info("gpus:\n");
	for(const gal::physical_device_info &phy : gpu_list.physical_devices) {
		osal::this_terminal::info("  "sv,phy.pci.domain,':',phy.pci.bus,':',phy.pci.device,':',phy.pci.function,'\n');
		osal::this_terminal::info("    "sv,phy.device->name, " = "sv, phy.device->id, '\n');
		osal::this_terminal::info("    "sv,phy.device->vendor->name, " = "sv, phy.device->vendor->id, '\n');
	}

	gal::init_settings_window winsett;
	winsett.win_back = gal::window_backend::xcb;
	winsett.soft_info = softinfo;
	if(!gal::initialize(std::move(winsett))) {
		gal::shutdown();
		//gamemode_request_end();
		return 3;
	}

	//gal::select_desktop(0);

	/*gal::init_settings_render rndrsett;
	rndrsett.ctx_back = gal::render_ctx_backend::vulkan;
	rndrsett.rndr_back = gal::render_backend::vulkan;
	rndrsett.soft_info = softinfo;
	if(!gal::initialize(std::move(std::move(rndrsett)))) {
		gal::shutdown();
		//gamemode_request_end();
		return 4;
	}

	osal::this_terminal::info("vulkan support:\n");
	for(const gal::physical_device_info &phy : gpu_list.physical_devices) {
		osal::this_terminal::info("  "sv,phy.pci.domain,':',phy.pci.bus,':',phy.pci.device,':',phy.pci.function,'\n');
		osal::this_terminal::info("    "sv,gal::gpu_supported(phy.pci),'\n');
	}

	if(!gal::select_gpu(gpu_list.physical_devices[0].pci)) {
		gal::shutdown();
		//gamemode_request_end();
		return 5;
	}*/

	gal::window test{gal::dimension{1600, 900}};
	gal::pen tpen{test};

	gal::font fnt{*gal::query_font(""sv)};

	test.draw = [&tpen,&fnt,&test]() noexcept -> void {
		tpen.point({
			gal::point{10, 10},
			gal::point{10, 20},
			gal::point{20, 10},
			gal::point{20, 20}
		}, false);
		tpen.line({
			gal::point{50, 10},
			gal::point{ 5, 20},
			gal::point{25,-20},
			gal::point{10, 10}
		}, true);
		tpen.segment({
			gal::segment{{100, 10}, {140, 30}},
			gal::segment{{110, 25}, {130, 60}}
		});
		tpen.rectangle({
			gal::rectangle{10, 50, 40, 20},
			gal::rectangle{80, 50, 10, 40}
		}, false);
		tpen.arc({
			gal::arc{10, 100, 60, 40, {0, 90 << 6}},
			gal::arc{90, 100, 55, 40, {0, 270 << 6}}
		}, false);
		gal::glyph_set glyps{fnt.compose("test"sv)};
		glyps.render(test, 0, 0);
	};

	bool should_quit{false};
	test.on_close = [&should_quit]() noexcept -> void {
		should_quit = true;
	};

	while(!should_quit) {
		gal::upkeep();
	}

	gal::shutdown();
	//gamemode_request_end();

	return 0;
}

extern "C"
{
	CTL_NO_DECL_BEGIN
	CTL_SHARED_EXPORT std::int32_t AmdPowerXpressRequestHighPerformance = 1;
	CTL_SHARED_EXPORT std::uint32_t NvOptimusEnablement = 0x00000001;
	CTL_NO_DECL_END
}
