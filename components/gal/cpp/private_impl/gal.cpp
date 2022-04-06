#include <gal/gal.hpp>
#include "window.hpp"
#include "gal.hpp"
#include "font.hpp"

#if CTL_TARGET_OS & CTL_OS_FLAG_UNIX
extern "C"
{
	#include <pci/pci.h>
}
#endif

#include "xcb/api.hpp"
#include "vulkan/api.hpp"

namespace gal
{
	namespace __private
	{
		using initialize_t = void(*)();
		using upkeep_t = void(*)();
		using shutdown_t = void(*)();
	}

	namespace __rndr
	{
		using initialize_t = bool(*)();

		static render_backend backend;

		CTL_NO_DECL_BEGIN
		bool initalized{false};
		CTL_NO_DECL_END

		static initialize_t init;
		//static __private::upkeep_t upkeep;
		static __private::shutdown_t shutdown;

		using create_impl_t = __rndr::impl *(*)(__win::impl &);
		static create_impl_t create_impl;
	}

	namespace __win
	{
		static window_backend backend;

		static __private::initialize_t init;
		static __private::upkeep_t upkeep;
		static __private::shutdown_t shutdown;

		CTL_NO_DECL_BEGIN
		create_impl_t create_impl;
		CTL_NO_DECL_END

		using get_nat_win_t = std::uintptr_t(*)(__win::impl &);
		using get_nat_conn_t = std::uintptr_t(*)(__win::impl &);

		static get_nat_conn_t get_nat_conn;
		static get_nat_win_t get_nat_win;
	}

	namespace __font
	{
		CTL_NO_DECL_BEGIN
		create_glyps_t create_glyph_set;
		CTL_NO_DECL_END
	}

	namespace __private
	{
		GAL_SHARED_API window_backend GAL_SHARED_API_CALL get_win_backend() noexcept
		{ return __win::backend; }

		GAL_SHARED_API std::uintptr_t GAL_SHARED_API_CALL get_nat_win(__win::impl &win) noexcept
		{ return __win::get_nat_win(win); }
		GAL_SHARED_API std::uintptr_t GAL_SHARED_API_CALL get_nat_conn(__win::impl &win) noexcept
		{ return __win::get_nat_conn(win); }

		GAL_SHARED_API __rndr::impl * GAL_SHARED_API_CALL create_rndr_impl(__win::impl &win) noexcept
		{ return __rndr::create_impl(win); }
	}

	GAL_SHARED_API std::vector<std::string> GAL_SHARED_API_CALL collect_desktops() noexcept
	{
		switch(__win::backend) {
			case window_backend::xcb: {
				return xcb::collect_desktops();
			}
			default: {
				CTL_DEBUGTRAP;
				return {};
			}
		}
	}

	GAL_SHARED_API void GAL_SHARED_API_CALL select_desktop(std::size_t desk) noexcept
	{
		switch(__win::backend) {
			case window_backend::xcb: {
				return xcb::select_desktop(desk);
			}
			default: {
				CTL_DEBUGTRAP;
			}
		}
	}

	GAL_SHARED_API std::vector<monitor_info> GAL_SHARED_API_CALL collect_monitors() noexcept
	{
		switch(__win::backend) {
			case window_backend::xcb: {
				return xcb::collect_monitors();
			}
			default: {
				CTL_DEBUGTRAP;
				return {};
			}
		}
	}

	GAL_SHARED_API void GAL_SHARED_API_CALL select_monitor(const monitor_dimension &mon) noexcept
	{
		switch(__win::backend) {
			case window_backend::xcb: {
				return xcb::select_monitor(mon);
			}
			default: {
				CTL_DEBUGTRAP;
			}
		}
	}

	GAL_SHARED_API gpu_list GAL_SHARED_API_CALL collect_gpus() noexcept
	{
	#if CTL_TARGET_OS & CTL_OS_FLAG_UNIX
		gpu_list list;

		pci_access *pci_acc{pci_alloc()};
		pci_init(pci_acc);
		pci_scan_bus(pci_acc);

		static const auto find_vendor{[&list](std::size_t id) noexcept -> const vendor_info * {
			for(const vendor_info &it : list.vendors) {
				if(it.id == id) {
					return &it;
				}
			}
			return nullptr;
		}};

		static const auto find_device{[&list](std::size_t vend_id, std::size_t id) noexcept -> const device_info * {
			for(const device_info &it : list.devices) {
				if(it.vendor->id == vend_id && it.id == id) {
					return &it;
				}
			}
			return nullptr;
		}};

		pci_dev *dev{pci_acc->devices};
		while(dev) {
			pci_fill_info(dev, PCI_FILL_CLASS);

			bool is_graphics{false};

			switch(dev->device_class) {
				case PCI_CLASS_DISPLAY_VGA:
				{ is_graphics = true; break; }
				case PCI_CLASS_DISPLAY_OTHER:
				{ is_graphics = true; break; }
			}

			if(is_graphics) {
				pci_fill_info(dev, PCI_FILL_IDENT|PCI_FILL_PHYS_SLOT);

				const std::size_t vendor_id{dev->vendor_id};

				const vendor_info *ven_info{find_vendor(vendor_id)};
				if(!ven_info) {
					vendor_info &tmp_ven_info{list.vendors.emplace_back()};
					tmp_ven_info.id = vendor_id;

					char vendor_name[1024];
					pci_lookup_name(pci_acc, vendor_name, sizeof(vendor_name), PCI_LOOKUP_VENDOR, vendor_id);

					tmp_ven_info.name = std::move(vendor_name);

					ven_info = &tmp_ven_info;
				}

				const std::size_t device_id{dev->device_id};

				const device_info *dev_info{find_device(vendor_id, device_id)};
				if(!dev_info) {
					device_info &tmp_dev_info{list.devices.emplace_back(*ven_info)};
					tmp_dev_info.id = device_id;

					char device_name[1024];
					pci_lookup_name(pci_acc, device_name, sizeof(device_name), PCI_LOOKUP_DEVICE, vendor_id, device_id);

					tmp_dev_info.name = std::move(device_name);

					dev_info = &tmp_dev_info;
				}

				physical_device_info &phy_dev{list.physical_devices.emplace_back(*dev_info)};

				phy_dev.pci.domain = static_cast<std::size_t>(dev->domain);
				phy_dev.pci.bus = dev->bus;
				phy_dev.pci.device = dev->dev;
				phy_dev.pci.function = dev->func;
			}

			dev = dev->next;
		}

		pci_cleanup(pci_acc);

		return list;
	#else
		#error
	#endif
	}

	GAL_SHARED_API bool GAL_SHARED_API_CALL gpu_supported(const pci &gpu) noexcept
	{
		ctl::unique_ptr<__win::impl> tmp{__win::create_impl(std::nullopt, {0, 0, 800, 600})};

		switch(__rndr::backend) {
			case render_backend::vulkan: {
				return vulkan::gpu_supported(*tmp, gpu);
			}
			default: {
				CTL_DEBUGTRAP;
				return false;
			}
		}
	}

	GAL_SHARED_API bool GAL_SHARED_API_CALL select_gpu(const pci &gpu) noexcept
	{
		switch(__rndr::backend) {
			case render_backend::vulkan: {
				return vulkan::select_gpu(gpu);
			}
			default: {
				CTL_DEBUGTRAP;
				return false;
			}
		}
	}

	GAL_SHARED_API bool GAL_SHARED_API_CALL initialize(const init_settings_window &settings) noexcept
	{
		__win::backend = settings.win_back;

		switch(settings.win_back) {
			case window_backend::xcb: {
				__win::create_impl = xcb::create_window;
				__win::init = xcb::initialize;
				__win::upkeep = xcb::upkeep;
				__win::shutdown = xcb::shutdown;
				__win::get_nat_win = xcb::get_native_window;
				__win::get_nat_conn = xcb::get_native_connection;
				__font::create_glyph_set = xcb::create_glyphs;
				break;
			}
			default:
			{ return false; }
		}

		if(settings.win_back == window_backend::xcb) {
			xcb::set_software_info(settings.soft_info);
		}

		font_manager::init();

		__win::init();

		return true;
	}

	GAL_SHARED_API bool GAL_SHARED_API_CALL initialize(const init_settings_render &settings) noexcept
	{
		if(settings.rndr_back == render_backend::vulkan &&
			settings.ctx_back != render_ctx_backend::vulkan) {
			return false;
		} else if(settings.rndr_back == render_backend::opengl &&
					settings.ctx_back == render_ctx_backend::vulkan) {
			return false;
		}

		__rndr::backend = settings.rndr_back;
		__rndr::initalized = true;

		switch(settings.ctx_back) {
			case render_ctx_backend::vulkan:
			{ break; }
			default:
			{ return false; }
		}

		switch(settings.rndr_back) {
			case render_backend::vulkan: {
				__rndr::create_impl = vulkan::create_renderer;
				__rndr::init = vulkan::initialize;
				__rndr::shutdown = vulkan::shutdown;
				break;
			}
			default:
			{ return false; }
		}

		if(settings.rndr_back == render_backend::vulkan) {
			vulkan::set_software_info(settings.soft_info);
		}

		return __rndr::init();
	}

	GAL_SHARED_API void GAL_SHARED_API_CALL upkeep() noexcept
	{
		__win::upkeep();
	}

	GAL_SHARED_API void GAL_SHARED_API_CALL shutdown() noexcept
	{
		if(__rndr::initalized) {
			__rndr::shutdown();
		}
		__win::shutdown();
		font_manager::shutdown();
	}
}
