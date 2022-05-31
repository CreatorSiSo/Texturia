import { defineConfig, UserConfig } from "vite";
import vue from "@vitejs/plugin-vue";

const baseConfig: UserConfig = {
	resolve: {
		alias: {
			"@/": new URL("./src/", import.meta.url).pathname,
		},
	},
	plugins: [vue()],
};

// https://vitejs.dev/config/
export default defineConfig(({ command, mode }) => {
	if (command === "serve") {
		// development config
		return {
			...baseConfig,
			build: { minify: false },
		};
	} else {
		// production config
		return {
			...baseConfig,
			build: {
				outDir: "dist",
				target: "es2015",
				minify: "esbuild",
			},
			esbuild: {
				minify: true,
				legalComments: "eof",
			},
		};
	}
});
