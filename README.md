# mruby-file-mknod   [![Build Status](https://travis-ci.org/udzura/mruby-file-mknod.svg?branch=master)](https://travis-ci.org/udzura/mruby-file-mknod)

Add class method `File.mknod/File.majorminor`

## install by mrbgems

Add conf.gem line to `build_config.rb`

```ruby
MRuby::Build.new do |conf|
  conf.gem :github => 'udzura/mruby-file-mknod'
end
```
## example

```ruby
File.majorminor "/dev/urandom"
# => {:major=>1, :minor=>9, :filetype=>:char}
File.majorminor "/dev/sda"
# => {:major=>8, :minor=>0, :filetype=>:block}
File.majorminor "/dev/pts/2"
# => {:major=>136, :minor=>2, :filetype=>:char}

# Creating device requires you a `cap_mknod` privilege
# try: sudo setcap cap_mknod+ep ./mruby/bin/mirb 

File.mknod(:char, "/tmp/urandom", 1, 9)
# => true
```

```
$ head -c 64 /tmp/urandom | od -x 
0000000 e8d2 b498 c34d 8941 3670 4c12 2291 bc02
0000020 fe85 2d63 a4fb 142d 280b ef62 ba6e 11e7
0000040 209f f487 108a 5e33 fd0d e778 5ae5 8988
0000060 42de 2e88 28c9 9aa3 1f35 b1ec 0282 b251
0000100
```

## License

Under the MIT License: see LICENSE file
