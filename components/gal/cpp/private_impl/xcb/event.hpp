#pragma once

#include <ctl/version>
#include "window.hpp"
#include "message.hpp"
#include "xcb.hpp"

namespace gal::xcb
{
	class CTL_LOCAL_CLASS client_message_event final
	{
		using win_t = gal::xcb::window;

	public:
		client_message_event(client_message_event &&) noexcept = default;
		client_message_event &operator=(client_message_event &&) noexcept = default;

		template <typename T>
		T data(std::size_t i = 0) const noexcept = delete;

		inline ctl::optional_ref<win_t> window() noexcept
		{ return win; }

		template <typename T>
		inline T cast() const noexcept
		{
			static_assert(alignof(T) == alignof(xcb_client_message_data_t));
			static_assert(sizeof(T) <= sizeof(xcb_client_message_data_t));
			static_assert(sizeof(T) >= sizeof(xcb_atom_t));
			return ctl::type_cast<T>(evnt->data);
		}

		inline xcb_atom_t type() const noexcept
		{ return evnt->type; }
		xcb_atom_t msg() const noexcept;

	private:
		friend class generic_event;

		client_message_event(const client_message_event &) noexcept = delete;
		client_message_event &operator=(const client_message_event &) noexcept = delete;

		inline client_message_event(const xcb_client_message_event_t *ptr) noexcept
			: evnt{ptr}
		{
			if(evnt) {
				win = win_t::find(evnt->window);
			}
		}

		const xcb_client_message_event_t *evnt;
		ctl::optional_ref<win_t> win;
	};

	template <>
	inline std::uint8_t client_message_event::data<std::uint8_t>(std::size_t i) const noexcept
	{ return evnt->data.data8[i]; }
	template <>
	inline std::uint16_t client_message_event::data<std::uint16_t>(std::size_t i) const noexcept
	{ return evnt->data.data16[i]; }
	template <>
	inline std::uint32_t client_message_event::data<std::uint32_t>(std::size_t i) const noexcept
	{ return evnt->data.data32[i]; }

	inline xcb_atom_t client_message_event::msg() const noexcept
	{ return static_cast<xcb_atom_t>(data<std::uint32_t>(0)); }

	class CTL_LOCAL_CLASS destroy_notify_event final
	{
		using win_t = gal::xcb::window;

	public:
		destroy_notify_event(destroy_notify_event &&) noexcept = default;
		destroy_notify_event &operator=(destroy_notify_event &&) noexcept = default;

		inline ctl::optional_ref<win_t> window() noexcept
		{ return win; }

	private:
		friend class generic_event;

		destroy_notify_event(const destroy_notify_event &) noexcept = delete;
		destroy_notify_event &operator=(const destroy_notify_event &) noexcept = delete;

		inline destroy_notify_event(const xcb_destroy_notify_event_t *ptr) noexcept
			: evnt{ptr}
		{
			if(evnt) {
				win = win_t::find(evnt->window);
			}
		}

		const xcb_destroy_notify_event_t *evnt;
		ctl::optional_ref<win_t> win;
	};

	class CTL_LOCAL_CLASS expose_event final
	{
		using win_t = gal::xcb::window;

	public:
		expose_event(expose_event &&) noexcept = default;
		expose_event &operator=(expose_event &&) noexcept = default;

		inline ctl::optional_ref<win_t> window() noexcept
		{ return win; }

		std::size_t x;
		std::size_t y;
		std::size_t width;
		std::size_t height;

	private:
		friend class generic_event;

		expose_event(const expose_event &) noexcept = delete;
		expose_event &operator=(const expose_event &) noexcept = delete;

		inline expose_event(const xcb_expose_event_t *ptr) noexcept
			: evnt{ptr}
		{
			if(evnt) {
				win = win_t::find(evnt->window);
				x = static_cast<std::size_t>(evnt->x);
				y = static_cast<std::size_t>(evnt->y);
				width = static_cast<std::size_t>(evnt->width);
				height = static_cast<std::size_t>(evnt->height);
			}
		}

		const xcb_expose_event_t *evnt;
		ctl::optional_ref<win_t> win;
	};

	class CTL_LOCAL_CLASS configure_notify_event final
	{
		using win_t = gal::xcb::window;

	public:
		configure_notify_event(configure_notify_event &&) noexcept = default;
		configure_notify_event &operator=(configure_notify_event &&) noexcept = default;

		inline ctl::optional_ref<win_t> window() noexcept
		{ return win; }

		std::size_t x;
		std::size_t y;
		std::size_t width;
		std::size_t height;

	private:
		friend class generic_event;

		configure_notify_event(const configure_notify_event &) noexcept = delete;
		configure_notify_event &operator=(const configure_notify_event &) noexcept = delete;

		inline configure_notify_event(const xcb_configure_notify_event_t *ptr) noexcept
			: evnt{ptr}
		{
			if(evnt) {
				win = win_t::find(evnt->window);
				x = static_cast<std::size_t>(evnt->x);
				y = static_cast<std::size_t>(evnt->y);
				width = static_cast<std::size_t>(evnt->width);
				height = static_cast<std::size_t>(evnt->height);
			}
		}

		const xcb_configure_notify_event_t *evnt;
		ctl::optional_ref<win_t> win;
	};

	class CTL_LOCAL_CLASS generic_event final
	{
	public:
		generic_event() noexcept = default;

		inline  generic_event(generic_event &&other) noexcept
			: evnt{std::move(other.evnt)}
		{ other.evnt = nullptr; }

		inline generic_event &operator=(generic_event &&other) noexcept
		{
			evnt = std::move(other.evnt);
			other.evnt = nullptr;
			return *this;
		}

		inline ~generic_event() noexcept
		{
			if(evnt) {
				delete evnt;
			}
		}

		inline explicit operator bool() const noexcept
		{ return !!evnt; }

		inline std::uint8_t type() const noexcept
		{ return XCB_EVENT_RESPONSE_TYPE(evnt); }

		inline explicit operator client_message_event() const noexcept
		{ return client_message_event{reinterpret_cast<const xcb_client_message_event_t *>(evnt)}; }
		inline explicit operator destroy_notify_event() const noexcept
		{ return destroy_notify_event{reinterpret_cast<const xcb_destroy_notify_event_t *>(evnt)}; }
		inline explicit operator expose_event() const noexcept
		{ return expose_event{reinterpret_cast<const xcb_expose_event_t *>(evnt)}; }
		inline explicit operator configure_notify_event() const noexcept
		{ return configure_notify_event{reinterpret_cast<const xcb_configure_notify_event_t *>(evnt)}; }

		inline operator const xcb_generic_event_t *() const noexcept
		{ return evnt; }

	private:
		friend class connection;

		inline generic_event(const xcb_generic_event_t *ptr) noexcept
			: evnt{ptr}
		{
		}

		generic_event(const generic_event &) noexcept = delete;
		generic_event &operator=(const generic_event &) noexcept = delete;

		const xcb_generic_event_t *evnt{nullptr};
	};
}
