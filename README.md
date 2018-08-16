# Xcselect

`Xcselect` is a command line tool alternative to `xcode-select --switch <path>` that manages multiple versions of Xcode.

## Features
- Switch to another version of Xcode simpler
- Locate all versions of Xcode in your Applications folder automatically

## Usage
```
$ xcselect <xcode_version> [--version] [--help]
```

### Examples
```
$ xcselect 9.4.1
$ xcselect 8.2.1
$ xcselect 7.3.1
```

## Install Xcselect

### Homebrew
If you have [Homebrew][1] installed, install Xcselect via

```
$ brew tap pandawebsoft/xcselect && brew install xcselect
```

### Shell Script
The commands below is another alternative to install Xcselect.

```
$ git clone https://github.com/pandawebsoft/xcselect.git --depth 1 ./tmp && ./tmp/tools/install && rm -rf tmp
```

## Uninstall Xcselect

### Homebrew

```
$ brew uninstall xcselect && brew untap pandawebsoft/xcselect
```

### Shell Script

```
$ git clone https://github.com/pandawebsoft/xcselect.git --depth 1 ./tmp && ./tmp/tools/uninstall && rm -rf tmp
```

## License

The [MIT license][2]


 [1]: http://brew.sh/
 [2]: https://github.com/pandawebsoft/xcselect/blob/master/LICENSE
