CFLAGS += -Werror -Wall

pam_self.so: self.c
	gcc $(CFLAGS) -fPIC -shared -Xlinker -x -o $@ $< -lcurl

