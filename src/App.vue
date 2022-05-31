<template>
	<div class="w-full h-full p-[0.6rem] select-none">
		<Layout direction="row">
			<Editor :elevation="0"></Editor>
			<Editor :elevation="1"></Editor>
			<Layout direction="col">
				<Editor :elevation="1"></Editor>
				<Editor :elevation="1"></Editor>
			</Layout>
		</Layout>
	</div>
</template>

<script setup lang="ts">
import Layout from '@/components/Layout.vue'
import Editor from '@/components/Editor.vue'
</script>
