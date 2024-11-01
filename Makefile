CFLAGS += -Werror -Wall

pam_self.so: self_pam.c
	gcc $(CFLAGS) -fPIC -shared -Xlinker -x -o $@ $< -lcurl
