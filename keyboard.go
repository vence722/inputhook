package inputhook

/*
extern void hook(int hType);
*/
import "C"

type KeyboardHookCallback func(keyEvent int, keyCode int)

var mKeyboardCallback KeyboardHookCallback

func HookKeyboard(callback KeyboardHookCallback) {
	mKeyboardCallback = callback
	C.hook(HOOK_TYPE_KEYBOARD)
}

//export keyboardCallback
func keyboardCallback(keyEvent C.int, keyCode C.int) {
	if mKeyboardCallback != nil {
		mKeyboardCallback(int(keyEvent), int(keyCode))
	}
}
