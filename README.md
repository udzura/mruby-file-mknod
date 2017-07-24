# mruby-file-mknod   [![Build Status](https://travis-ci.org/udzura/mruby-file-mknod.svg?branch=master)](https://travis-ci.org/udzura/mruby-file-mknod)
File class
## install by mrbgems
- add conf.gem line to `build_config.rb`

```ruby
MRuby::Build.new do |conf|

    # ... (snip) ...

    conf.gem :github => 'udzura/mruby-file-mknod'
end
```
## example
```ruby
p File.hi
#=> "hi!!"
t = File.new "hello"
p t.hello
#=> "hello"
p t.bye
#=> "hello bye"
```

## License
under the MIT License:
- see LICENSE file
