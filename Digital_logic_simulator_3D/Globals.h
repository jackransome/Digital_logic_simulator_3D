#include "Graphics.h"
#include "Input.h"

namespace globals
{
	using std::shared_ptr;

	extern Graphics gfx;
	extern Input input;

	extern const float dt;
	extern const float dtSeconds;

	void globalInit();
}