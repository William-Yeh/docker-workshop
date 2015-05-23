// Directory walker, excluding /dev /proc /sys.
//
// Usage: walk  [starting path]
//
// adapted from: https://raw.githubusercontent.com/kr/fs/master/example_test.go
//

package main

import (
	"fmt"
	"os"
	"regexp"
	"strconv"

	"github.com/kr/fs"
	"text/tabwriter"
)

var REGEX_EXCLUDE_PATH = regexp.MustCompile(`^/(dev|proc|sys)`)

const DATE_LAYOUT string = "2006-01-02 15:04"

var starting_path = "."

func main() {

	if len(os.Args) > 1 {
		starting_path = os.Args[1]
	}

	w := new(tabwriter.Writer)
	w.Init(os.Stdout, 2, 0, 1, ' ', tabwriter.AlignRight)

	walker := fs.Walk(starting_path)
	for walker.Step() {
		if err := walker.Err(); err != nil {
			fmt.Fprintln(os.Stderr, err)
			continue
		}
		path := walker.Path()
		if REGEX_EXCLUDE_PATH.FindStringSubmatch(path) != nil {
			continue
		}

		info := walker.Stat()
		file_type := "f"
		if info.IsDir() {
			file_type = "d"
		}

		fmt.Fprintln(w, file_type+" \t"+(info.ModTime().Format(DATE_LAYOUT)+" \t"+strconv.FormatInt(info.Size(), 10)+"\t\t"+path))
	}
	w.Flush()
}
