module.exports = {
  title: "Rescript Apollo Client",
  tagline: "Rescript bindings for the Apollo Client ecosystem",
  url: "https://reasonml-community.github.io/reason-apollo-client",
  // baseUrl: '/reason-apollo-client/',
  baseUrl: "/reason-apollo-client/",
  onBrokenLinks: "throw",
  favicon: "img/favicon.ico",
  organizationName: "reasonml-community", // Usually your GitHub org/user name.
  projectName: "reason-apollo-client", // Usually your repo name.
  themeConfig: {
    colorMode: {
      // Hides the switch in the navbar
      // Useful if you want to support a single color mode
      disableSwitch: true,
    },
    navbar: {
      title: "Rescript Apollo Client",
      logo: {
        alt: "Rescript Apollo Client Logo",
        src: "img/small_logo.png",
      },
      items: [
        {
          to: "docs/",
          activeBasePath: "docs",
          label: "Docs",
          position: "left",
        },
        { to: "docs/changelog", label: "Changelog", position: "left" },
        { to: "docs/examples", label: "Examples", position: "left" },
        { to: "docs/contributing", label: "Contributing", position: "right" },
        {
          href: "https://github.com/reasonml-community/reason-apollo-client",
          label: "GitHub",
          position: "right",
        },
      ],
    },
    footer: {
      style: "dark",
      copyright: `Copyright © ${new Date().getFullYear()} Reason Apollo Client. Built with Docusaurus.`,
    },
  },
  presets: [
    [
      "@docusaurus/preset-classic",
      {
        docs: {
          sidebarPath: require.resolve("./sidebars.js"),
          // Please change this to your repo.
          editUrl:
            "https://github.com/reasonml-community/reason-apollo-client/edit/master/website",
        },
        theme: {
          customCss: require.resolve("./src/css/custom.css"),
        },
      },
    ],
  ],
};
