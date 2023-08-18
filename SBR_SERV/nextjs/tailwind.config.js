const { nextui } = require("@nextui-org/react");

module.exports = {
	content: [
		"./src/pages/**/*.{js,ts,jsx,tsx,mdx}",
		"./src/components/**/*.{js,ts,jsx,tsx,mdx}",
		"./src/app/**/*.{js,ts,jsx,tsx,mdx}",
		"./node_modules/@nextui-org/theme/dist/**/*.{js,ts,jsx,tsx}",
	],
	theme: {
		extend: {
        },
	},
	darkMode: "class",
	plugins: [
		nextui({
			themes: {
				mytheme: {
					// custom theme
                    extend: "dark",
					colors: {
						background: "#282a36",
                        divider: "#44475a",
						foreground: "#f8f8f2",
						focus: "#BEF264",
					},
				},
			},
		}),
	],
};
