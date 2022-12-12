cask "kicad-minimal" do
  version "6.0.9-0"
  sha256 "b6371b9fc9f68ec0b0e4c8bd4e81871f6de49156ec75ba632854d155cfb02cbe"

  url "https://github.com/ohmtech-rdi/kicad-releases-mirror/releases/download/6.0.9-0/kicad-minimal-6.0.9-0.dmg",
      verified: "github.com/"
  name "KiCad"
  desc "Electronics design automation suite"
  homepage "https://kicad.org/"

  depends_on macos: ">= :catalina"

  suite "KiCad"
  artifact "demos", target: "/Library/Application Support/kicad/demos"

  zap trash: [
    "/Library/Application Support/kicad",
    "~/Library/Application Support/kicad",
    "~/Library/Preferences/kicad",
    "~/Library/Preferences/org.kicad-pcb.*",
  ]
end
