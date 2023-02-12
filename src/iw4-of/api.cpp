#include "std_include.hpp"

#include "assets/assets.hpp"
#include "api.hpp"

iw4of::api::~api()
{
	delete(_assets);
}

iw4of::api::api(const params_t& params)
{
	_assets = new assets(params);
}

bool iw4of::api::write(int t, void* asset) const
{
	return _assets->write<void>(t, asset);
}

void* iw4of::api::read(int t, std::string name) const
{
	return _assets->read<void>(t, name);
}
