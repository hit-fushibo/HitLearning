package main

import (
	"fmt"
	"html/template"
	"net/http"
)

func helloHandleFunc(w http.ResponseWriter, r *http.Request) {
	t, err := template.ParseFiles("./test.tmpl")
	if err != nil {
		fmt.Println("error:", err)
		return
	}
	name := "i love go"
	t.Execute(w, name)
}

func main() {
	http.HandleFunc("/", helloHandleFunc)
	http.ListenAndServe(":8086", nil)
}
