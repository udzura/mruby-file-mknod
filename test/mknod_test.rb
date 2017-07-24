##
## File Test
##

assert("File.majorminor") do
  t = File.majorminor("/dev/null")
  assert_equal(1, t[:major])
  assert_equal(3, t[:minor])
  assert_equal(:char, t[:filetype])
end
