#pragma once

#include <ctl/version>
#include <ctl/optional>
#include "vulkan.hpp"
#include "instance.hpp"

namespace gal::vulkan
{
	class CTL_LOCAL_CLASS device final
	{
	public:
		device(device &&) noexcept = default;
		device &operator=(device &&) noexcept = default;

		device(const vk::raii::PhysicalDevice &phy, const instance &inst, const vk::raii::SurfaceKHR &surf) noexcept;

		inline void reset() noexcept
		{ handle.reset(); }

		inline const vk::raii::Device &operator*() const noexcept
		{ return *handle; }
		inline const vk::raii::Device *operator->() const noexcept
		{ return handle.get(); }

		inline bool exclusive_queue() const noexcept
		{ return queues.exclusive(); }

		inline const std::vector<std::uint32_t> &queue_indexes() const noexcept
		{ return queues.idxs(); }

		vk::raii::ImageView create_image_view(vk::Image img, vk::Format fmt, vk::ImageAspectFlags aspect, std::size_t miplevel) noexcept;
		vk::raii::RenderPass create_render_pass(vk::Format clrfmt, vk::Format depthfmt, vk::SampleCountFlagBits samples) noexcept;

		static vk::Format find_supported_format(const vk::raii::PhysicalDevice &phy, std::initializer_list<vk::Format> wanted, vk::ImageTiling tiling, vk::FormatFeatureFlags features) noexcept;

		static inline vk::Format find_depth_format(const vk::raii::PhysicalDevice &phy) noexcept
		{
			return find_supported_format(
				phy,
				{
					vk::Format::eD32Sfloat,
					vk::Format::eD32SfloatS8Uint,
					vk::Format::eD24UnormS8Uint,
				},
				vk::ImageTiling::eOptimal,
				vk::FormatFeatureFlagBits::eDepthStencilAttachment
			);
		}

		static bool has_complete_queue_family(const vk::raii::PhysicalDevice &phy, const vk::raii::SurfaceKHR &surf) noexcept;
		static bool extensions_supported(const vk::raii::PhysicalDevice &phy) noexcept;

	#if CTL_DEBUG_LEVEL > 0
		template <typename T>
		inline void set_name(const T &obj, std::string_view name) noexcept
		{
			handle->setDebugUtilsObjectNameEXT(
				vk::DebugUtilsObjectNameInfoEXT{
					T::objectType,
					reinterpret_cast<std::uint64_t>(vk_ext::native(obj)),
					name.data()
				}
			);
		}
	#endif

	private:
		device() = delete;
		device(const device &) = delete;
		device &operator=(const device &) = delete;

		ctl::unique_ptr<vk::raii::Device> handle;

		struct queue_list;

		struct queue final
		{
			inline queue(const std::uint32_t &idx_) noexcept
				: idx_ref{idx_}
			{
			}

			inline std::size_t idx() const noexcept
			{ return *idx_ref; }

			inline bool valid() const noexcept
			{ return (*idx_ref) != ~0u; }

		private:
			friend struct queue_list;

			ctl::cref_wrapper<std::uint32_t> idx_ref;
			ctl::unique_ptr<vk::raii::Queue> handle;
		};

		struct queue_list final
		{
			inline const queue &graphics() const noexcept
			{ return *graphics_; }
			inline const queue &present() const noexcept
			{ return *present_; }

			inline bool complete() const noexcept
			{ return graphics_ && present_; }

			inline bool exclusive() const noexcept
			{ return data.size() == 1; }

			inline const std::vector<std::uint32_t> &idxs() const noexcept
			{ return idxs_; }

			bool populate_idxs(const vk::raii::PhysicalDevice &phy, const vk::raii::SurfaceKHR &surf) noexcept;
			void populate_handles(const vk::raii::Device &dev) noexcept;
			void populate_info(std::vector<vk::DeviceQueueCreateInfo> &vec) noexcept;

		private:
			queue &allocate(std::size_t idx) noexcept;

			std::vector<std::uint32_t> idxs_;
			ctl::ptr_vector<queue> data;
			queue *graphics_{nullptr};
			queue *present_{nullptr};
		};

		queue_list queues;
	};
}
