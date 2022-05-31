<template>
	<div class="h-full w-full flex gap-[0.6rem]" :class="`flex-${direction}`">
		<slot></slot>
	</div>
</template>

<script setup lang="ts">
import { defineProps } from 'vue'

const props = defineProps<{
	direction: 'row' | 'col'
}>()
</script>
