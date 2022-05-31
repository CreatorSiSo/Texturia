<template>
	<section class="h-full w-full flex flex-col rounded-2xl" :class="background">
		<div class="h-8">
			<button>Switch</button>
			<slot name="bar">Top Bar</slot>
		</div>
		<div class="relative">
			<div class="z-10 absolute inset-0">
				<slot name="overlay">Overlay</slot>
			</div>
			<div class="z-0">
				<slot name="inner">Inner</slot>
			</div>
		</div>
	</section>
</template>

<script setup lang="ts">
import { computed, withDefaults } from 'vue'

const props = withDefaults(
	defineProps<{
		elevation?: 0 | 1
	}>(),
	{ elevation: 1 }
)

const background = computed(() => `bg-elevation-${props.elevation}`)
</script>
