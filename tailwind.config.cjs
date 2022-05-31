module.exports = {
	theme: {
		fontFamily: {
			sans: [
				'Manrope',
				'Impact',
				'Haettenschweiler',
				'Arial Narrow Bold',
				'sans-serif',
			],
			serif: [
				'Cinzel',
				'Cambria',
				'Cochin',
				'Georgia',
				'Times',
				'Times New Roman',
				'serif',
			],
		},
		extend: {
			colors: {
				'elevation-0': '#222222',
				'elevation-1': '#292929',
				'elevation-2': '#2F2F2F',
				'elevation-3': '#363636',
				'elevation-4': '#3D3D3D',
			},
		},
	},
	content: ['./index.html', './src/**/*.{vue,js,ts,jsx,tsx}'],
	purge: {
		options: {
			safelist: [{ pattern: /(bg)-(elevation)-(0|1|2|3|4)/ }],
		},
	},
	plugins: [],
}
