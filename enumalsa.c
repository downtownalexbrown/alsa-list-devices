#include <alsa/asoundlib.h>
#include <stdio.h>

#define unlikely(x) __builtin_expect((x),0)

void** hints;
int main() {
	if (snd_device_name_hint(-1, "pcm", &hints) < 0)  // checks for devices which support pulse core modulation
		return -1;

	for (size_t i = 0; hints[i] != NULL; i++) {
		void *hint = hints[i];

		char *name = snd_device_name_get_hint(hint, "NAME");
		char *desc = snd_device_name_get_hint(hint, "DESC");
		char *id = snd_device_name_get_hint(hint, "IOID");
		if (unlikely(name == NULL) || unlikely(desc == NULL) || unlikely(id == NULL)) // credit VLC, leads branch prediction towards false for optimization
			continue;

		printf("%s\n%s\n%s\n\n\n", name, desc, id);
	}

	snd_device_name_free_hint(hints);
	return 0;
}
