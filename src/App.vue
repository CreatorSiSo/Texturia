<template>
	<div
		class="h-full flex flex-col select-none cursor-default rounded-xl bg-background"
	>
		<div
			data-tauri-drag-region
			class="rounded-t-xl p-[.6rem] flex gap-4 justify-end bg-elevation-2"
		>
			<button
				ref="minimize"
				class="bg-yellow-400 rounded-lg p-[1px] h-[1.6rem] w-[1.6rem] text-black"
			>
				<svg
					xmlns="http://www.w3.org/2000/svg"
					preserveAspectRatio="xMidYMid meet"
					viewBox="0 0 24 24"
				>
					<path fill="currentColor" d="M20 14H4v-4h16" />
				</svg>
			</button>
			<button
				ref="maximize"
				class="bg-green-400 rounded-lg p-[1px] h-[1.6rem] w-[1.6rem] text-black"
			>
				<svg
					xmlns="http://www.w3.org/2000/svg"
					preserveAspectRatio="xMidYMid meet"
					viewBox="0 0 24 24"
				>
					<path fill="currentColor" d="M4 4h16v16H4V4m2 4v10h12V8H6Z" />
				</svg>
			</button>
			<button
				ref="close"
				class="bg-red-500 rounded-lg p-[1px] h-[1.6rem] w-[1.6rem] text-black"
			>
				<svg
					xmlns="http://www.w3.org/2000/svg"
					preserveAspectRatio="xMidYMid meet"
					viewBox="0 0 24 24"
				>
					<path
						fill="currentColor"
						d="M19 6.41L17.59 5L12 10.59L6.41 5L5 6.41L10.59 12L5 17.59L6.41 19L12 13.41L17.59 19L19 17.59L13.41 12L19 6.41Z"
					/>
				</svg>
			</button>
		</div>
		<div class="h-full p-[0.6rem]">
			<Layout direction="row">
				<Editor :elevation="0"></Editor>
				<Editor></Editor>
				<Layout direction="col">
					<Editor></Editor>
					<Editor></Editor>
				</Layout>
			</Layout>
		</div>
	</div>
</template>

<script setup lang="ts">
import { appWindow } from '@tauri-apps/api/window'
import { ref, onMounted, Ref } from 'vue'

import Layout from '@/components/Layout.vue'
import Editor from '@/components/Editor.vue'

const minimize: Ref<HTMLButtonElement | null> = ref(null)
const maximize: Ref<HTMLButtonElement | null> = ref(null)
const close: Ref<HTMLButtonElement | null> = ref(null)

onMounted(() => {
	minimize.value!.addEventListener('click', () => appWindow.minimize())
	maximize.value!.addEventListener('click', async () =>
		(await appWindow.isMaximized())
			? appWindow.unmaximize()
			: appWindow.maximize()
	)
	close.value!.addEventListener('click', () => appWindow.close())
})
</script>
