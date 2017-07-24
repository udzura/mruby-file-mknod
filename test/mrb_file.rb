##
## File Test
##

assert("File#hello") do
  t = File.new "hello"
  assert_equal("hello", t.hello)
end

assert("File#bye") do
  t = File.new "hello"
  assert_equal("hello bye", t.bye)
end

assert("File.hi") do
  assert_equal("hi!!", File.hi)
end
