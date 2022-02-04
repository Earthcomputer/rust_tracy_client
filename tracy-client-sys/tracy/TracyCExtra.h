#pragma once

#ifndef __cplusplus
#include <stdbool.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

	TRACY_API uint32_t __tracy_alloc_lockable_ctx(struct ___tracy_source_location_data const* srcloc);
	TRACY_API void __tracy_dealloc_lockable_ctx(uint32_t id);
	TRACY_API bool __tracy_lockable_ctx_before_lock(uint32_t id);
	TRACY_API void __tracy_lockable_ctx_after_lock(uint32_t id);
	TRACY_API void __tracy_lockable_ctx_after_unlock(uint32_t id);
	TRACY_API void __tracy_lockable_ctx_after_try_lock(uint32_t id, bool acquired);
	TRACY_API void __tracy_lockable_ctx_mark(uint32_t id, struct ___tracy_source_location_data const* srcloc);
	TRACY_API void __tracy_lockable_ctx_custom_name(uint32_t id, const char* name, size_t size);


#ifdef __cplusplus
}
#endif
