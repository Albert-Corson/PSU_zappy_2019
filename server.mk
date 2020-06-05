include var.mk sources.mk

override CPPFLAGS	+=	-I./share/include		\
						-I./server/include		\

override CFLAGS		+=	-Wall \
						-Wextra \
						-ffreestanding \
						-Wshadow \
						-Wsign-compare \
						-Wno-unused-parameter \
						-Wno-unused-variable \

$(NAME_SRV):	$(OBJ_SRV)
	$(LD) $^ $(LDFLAGS) $(LDLIBS) -o $@

.SECONDEXPANSION:
$(BUILD_SRV)/%.o:	%.c | $$(@D)/.
	$(CC) $(CPPFLAGS) $(CFLAGS) $(DEPFLAGS) -c $< -o $@

$(BUILD_SRV)/.:
	mkdir $@

$(BUILD_SRV)%/.:
	mkdir -p $@

.PRECIOUS: $(BUILD_SRV)/. $(BUILD_SRV)%/.
-include $(OBJ_SRV:.o=.d)
