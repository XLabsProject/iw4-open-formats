#pragma once
#include <game/structs.hpp>
#include <utils/memory.hpp>
#include <string>

namespace iw4of
{
	class asset_interface
	{
#define SHOULD_NOT_BE_NULL(x)\
	if (x == nullptr){\
		print_error("{} was unexpectedly null! could not find the asset for it", #x);\
		__debugbreak();\
	}

	public:
		template <typename T>
		bool write(T* header)
		{
			return write_internal({ header });
		}

		template <typename T>
		T* read(const std::string name)
		{
			return reinterpret_cast<T*>(read_internal(name));
		};

		asset_interface(const class assets* assets)
		{
			this->assets = assets;
		}

	protected:
		virtual void* read_internal(const std::string& name) const = 0;
		virtual bool write_internal(const native::XAssetHeader& header) const = 0;
		virtual std::filesystem::path get_file_path(const std::string& name) const = 0;

		mutable utils::memory::allocator local_allocator{};

		template <typename T>
		T* find(iw4of::native::XAssetType type, const std::string& name) const
		{
			return reinterpret_cast<T*>(this->find_internal(type, name));
		}

		template <typename... Args>
		void print(const std::string_view& fmt, Args&&... args) const
		{
			this->print_internal(std::vformat(fmt, std::make_format_args(args...)));
		}

		template <typename... Args>
		void print_error(const std::string_view& fmt, Args&&... args) const
		{
			this->print_error_internal(std::vformat(fmt, std::make_format_args(args...)));
		}


		const class assets* assets;

	private:
		void* find_internal(iw4of::native::XAssetType type, const std::string& name) const;
		void print_error_internal(const std::string& message) const;
		void print_internal(const std::string& message) const;
	};
}