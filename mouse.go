package inputhook

/*
extern void hook(int hType);
*/
import "C"

type MouseHookCallback func(x int64, y int64, event int, data uint64)

var mMouseCallback MouseHookCallback

func HookMouse(callback MouseHookCallback) {
	mMouseCallback = callback
	C.hook(HOOK_TYPE_MOUSE)
}

//export mouseCallback
func mouseCallback(x C.long, y C.long, event C.int, data C.ulong) {
	if mMouseCallback != nil {
		mMouseCallback(int64(x), int64(y), int(event), uint64(data))
	}
}
