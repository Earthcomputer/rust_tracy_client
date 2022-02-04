#include "TracyC.h"
#include "TracyCExtra.h"
#include "client/TracyLock.hpp"

class LockableCtxMirror
{
	uint32_t m_id;

	LockableCtxMirror(uint32_t id) : m_id(id) {}

	static LockableCtxMirror create_lockable_ctx(uint64_t srcloc)
	{
		// create LockableCtx without calling its destructor and cast it to a mirror
		char buffer[sizeof(LockableCtx) + alignof(LockableCtx)];
		char* aligned_buffer = buffer + alignof(LockableCtx) - reinterpret_cast<intptr_t>(buffer) % alignof(LockableCtx);
		LockableCtx* ctx = new (aligned_buffer) LockableCtx;
		return *reinterpret_cast<LockableCtxMirror*>(ctx);
	}

	LockableCtx& as_lockable_ctx()
	{
		return *reinterpret_cast<LockableCtx*>(this);
	}
};

TRACY_API uint32_t __tracy_alloc_lockable_ctx(uint64_t srcloc)
{
	return LockableCtxMirror::create_lockable_ctx(srcloc).m_id;
}

TRACY_API void __tracy_dealloc_lockable_ctx(uint32_t id)
{
	LockableCtxMirror(id).as_lockable_ctx().~LockableCtx();
}

TRACY_API bool __tracy_lockable_ctx_before_lock(uint32_t id)
{
	return LockableCtxMirror(id).as_lockable_ctx().BeforeLock();
}

TRACY_API void __tracy_lockable_ctx_after_lock(uint32_t id)
{
	LockableCtxMirror(id).as_lockable_ctx().AfterLock();
}

TRACY_API void __tracy_lockable_ctx_after_unlock(uint32_t id)
{
	LockableCtxMirror(id).as_lockable_ctx().AfterUnlock();
}

TRACY_API void __tracy_lockable_ctx_after_try_lock(uint32_t id, bool acquired)
{
	LockableCtxMirror(id).as_lockable_ctx().AfterTryLock();
}

TRACY_API void __tracy_lockable_ctx_mark(uint32_t id, uint64_t srcloc)
{
	LockableCtxMirror(id).as_lockable_ctx().Mark((const SourceLocationData*) srcloc);
}

TRACY_API void __tracy_lockable_ctx_custom_name(uint32_t id, const char* name, size_t size)
{
	LockableCtxMirror(id).as_lockable_ctx().CustomName(name, size);
}
