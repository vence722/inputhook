package inputhook

import (
	"fmt"
	"testing"
	"time"
)

const (
	TIME_FORMAT = "2006-01-02T15:04:05.9999"
)

func kbCallback(keyEvent int, keyCode int) {
	ts := time.Now().Format(TIME_FORMAT)
	fmt.Printf("[%s]Keyboard message: event[%d], keyCode[%d]\n", ts, keyEvent, keyCode)
}

func msCallback(x int64, y int64, event int, data uint64) {
	ts := time.Now().Format(TIME_FORMAT)
	fmt.Printf("[%s]Mouse message: x[%d], y[%d], event[%d], data[%d]\n", ts, x, y, event, data)
}

func TestHook(t *testing.T) {
	t.Log("start")
	go HookKeyboard(kbCallback)
	go HookMouse(msCallback)
	t.Log("hooked")
	ch := make(chan bool)
	<-ch
}
