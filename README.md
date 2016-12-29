inputhook
-----

A Go library for Windows that is used for hooking low-level user input. Could be used to log the keyboard and mouse event, or to do other things you want.

Usage
-----

First, you will need to define a callback function. For a keyboard event callback, the definition of function is like:
```
type KeyboardHookCallback func(keyEvent int, keyCode int)
```

An example of it:
```
func hookCallback(keyEvent int, keyCode int) {
	fmt.Println("keyEvent:", keyEvent)
	fmt.Println("keyCode:", keyCode)
}
```

Then in the main function, or the place you want to start listening to the input event, write the code like this:
```
inputhook.HookKeyboard(hookCallback)
```

This will make the keyboard hook start working. For a very simple completed demo, see as followed:
```
package main

import (
	"fmt"
	"github.com/vence722/inputhook"
)

func hookCallback(keyEvent int, keyCode int) {
	fmt.Println("keyEvent:", keyEvent)
	fmt.Println("keyCode:", keyCode)
}

func main() {
	inputhook.HookKeyboard(hookCallback)
	ch := make(chan bool)
	<-ch
}
```

For the mouse event hooking, it's very similar to the keyboard hook. One of the differences is it requires user to implement another callback function:
```
type MouseHookCallback func(x int64, y int64, event int, data uint64)
```

Then you should call HookMouse() to make the hooking work:
```
inputhook.HookMoused(hookCallback)
```

Have Fun!
-----
