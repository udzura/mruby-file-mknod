class File
  module Mknod
    module Device
      # Covering OCI's [default devices](https://github.com/opencontainers/runtime-spec/blob/master/config-linux.md#default-devices)
      def make_by_name(name, path, mode = 0644)
        case name
        when "null"
          ::File.mknod :char, path, 1, 3, mode
        when "zero"
          ::File.mknod :char, path, 1, 5, mode
        when "full"
          ::File.mknod :char, path, 1, 7, mode
        when "random"
          ::File.mknod :char, path, 1, 8, mode
        when "urandom"
          ::File.mknod :char, path, 1, 9, mode
        when "tty"
          ::File.mknod :char, path, 5, 0, mode
        when "console"
          ::File.mknod :char, path, 5, 1, mode
        when "ptmx"
          ::File.mknod :char, path, 5, 2, mode
        else
          raise "Unsupported device: #{name}"
        end
      end
      module_function :make_by_name

      %w(null zero full random urandom tty console ptmx).each do |nm|
        define_method "make_#{nm}" do |path, mode = 0644|
          self.make_by_name nm, path, mode
        end
        module_function "make_#{nm}".intern
      end
    end
  end
end
