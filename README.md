# 🪓 Remaining work
- [ ] TODO: SL in VSCode; SL in CLion (?)
  - Generate compilation database with `Bear make`
  - "Open folder" in VS Code (with SonarLine plugin installed). auto-configured the compilation DB produced by Bear
- [ ] TODO: quickfix
- [X] SC autoscan
  - clone the repository, add it to SonarCloud. the autoscan should start and finish quickly
- [X] SC CI-based. show the difference
  - prepare a branch with configured analysis, using build-wrapper.
    Also mention compilation database.
  - Show a new issue produced once the branch with analysis is merged and the GH Action finishes.
  - [X] Coverage generation and import
- [X] TODO: PR analysis. CaYC
  - Prepare a PR with different issues.
    Demonstrate that the quality gate mentions only the the issues on the changed and added code.
    Explain CaYC
- [ ] TODO: Bug/Code-Smell/Vulnerability
  Demonstrate different kinds of findings. Difference between a Bug and a Code-Smell.
  Special workflow for a vulnerability
- [ ] TODO: issue with secondaries
  show the short-cut navigation
- [ ] TODO: single-flow issue
- [X] TODO: multi-flow issue

# 📜 Storyboard

The goal of this demo is to show the analysis of a C++ application in SonarCloud.
We want to showcase how to apply the "Clean As You Code" methodology in practice.

We start with a legacy application.
This legacy application contains `main` branch with the existing code.
It also contains `add-feature` branch that represents a new feature we want to develop for the application.

The full set-up can either be done as part of the demo (takes about 15 minutes), or beforehand.
Branch `enable-ci-analysis` is available to move from Automatic Analysis to a CI-based analysis,
with the import of code coverage information.

Once the repository is fully set up, you can observe the concept of PR Quality Gate on new code
and its independence from the main code issues.
The application features basic, yet varied, issue types that can be detected by SonarCloud. In the PR, we have:

TODO: # * A simple bug with no secondary locations

TODO: # * A bug with a secondary location in another file

TODO: # * A bug with an execution flow

TODO: # * A bug with multiple flows

TODO: # * A "bad practice" code smell

TODO: # * A stylistic code smell

Additionally, we have a security hotspot on the `main` branch:

TODO: # * ???

When setting up CI-based analysis, import of code coverage will be done by default (in the `enable-ci-analysis` branch).

To demo SonarLint you can also clone this project to show the issues in SonarLint.
Some of the issues have quick fixes for them.

You can show the connected mode by simply following the tutorial in the IDE,
which allows

- the synchronization of silenced issues,
- custom quality profiles, and
- additional cross-TU issues.

# 🛠 Building and running the application

### Build Dependencies
- Install [git](https://git-scm.com/book/en/v2/Getting-Started-Installing-Git)
- Install [cmake](https://cmake.org/install/), if building with cmake
- Install libjson-c-dev, required by server target
- Install qtdeclarative5-dev, required by client target
- Install libpoppler-qt5-dev, required by client target

### Building with CMake
```shell
cmake -S . -B build

# Either build all available targets
cmake --build build --target all
# or build a specific target
cmake --build build --target server
```

### Building with Make
Building a specific target is also possible using make
```shell
make server
```

### Running the application
The executables will be put into the newly created `build` folder
 - `build/server` has to be run before the client
 - `build/client` is the GUI client interacting with the server

# 📝 Setup instructions

We are going to set up a SonarCloud analysis on this project.
We will visualize issues on the `main` branch and on pull requests and see how PRs get decorated automatically.

We will then set up a CI-based analysis and import code coverage information into the SonarCloud UI.

Useful link: https://docs.sonarcloud.io/

## 🛫 Getting Started

* Fork this project *with all branches*
  (untick the default checkbox, "Copy the `main` branch only").
* Go to https://sonarcloud.io/sessions/new and sign up with your GitHub account.
* Create a new organization under your name if there is none.
* Give SonarCloud permission to see the forked repository.

# 🎥 Demo

## 🤖 Automatic Analysis on SonarCloud

* Click ➕ in the top-right corner and select "Analyze new project"
* Select the forked repository.
* Click "Set Up"

Note two things, useful for the following step:

* Among the many detected issues,
  there is no report for [S1068: Unused "private" fields should be removed](https://rules.sonarsource.com/cpp/RSPEC-1068/).
  ![No S1068 issues detected](img/missing-issue-autoscan.png)
* Test-coverage metric is not computed.
  ![No coverage](img/missing-coverage.png)

## 👷 CI-based analysis on SonarCloud with a coverage display

This step assumes you have added the project to SonarCloud and executed automatic analysis (see the previous step).

For examples of CI-based analysis on other platforms, see https://github.com/sonarsource-cfamily-examples

* Click ⚙ "Administration" on the bottom-left and select "Analysis Method"
* Disable the "Automatic Analysis" switch.
* Generate a SonarCloud token:
  * Click on your profile picture in the top-right corner and select "My Account".
  * Select the "Security" tab.
  * Enter a token name (e.g. `cpp-demo`), and click on "Generate Token"
  * Copy the token to clipboard
* Enter the token to the repository secrets on GitHub
  * Select the ⚙ "Settings" tab of your repository
  * Select the "Secrets and variables"/"Actions" section
  * Click on "New Repository Secret"
  * Enter the name of the secret: `SONAR_TOKEN`
  * Paste the secret from the previous step.
  * Click "Add Secret".
* Checkout the `enable-ci-analysis` branch.
* In "sonar-project.properties" file change the `sonar.projectKey` and
  `sonar.organization` to use your organization name (your GitHub username).
* Commit, push, and merge the branch into `main` (careful: select yor fork as the target)
* After a couple of minutes, you should be able to see the analysis results on SonarCloud

Note that the total number of issues has reduced
because CI-based analysis analyses only the code you compile
in the configuration that you provide.
If a file is never compiled, it will not be analyzed, unlike with automatic analysis.
In particular, in this project, the "src/Client" target is not compiled automatically
on CI, so it is abscent in the compilation database and concequently not analyzed.

Note also that some issues appeared.
For example, the code smell: [S1068: Unused "private" fields should be removed](https://rules.sonarsource.com/cpp/RSPEC-1068/).
These issues cannot be confidently detected because they require knowledge of all places where the field might be used.
On one hand, if the automatic analysis could not figure out how to reach the place that uses the field,
it will miss it and falsely report a violation of this rule.
On the other hand, CI-based analysis is precise, it knows as much as your compiler.
If a field isn't used in any code that is compiled, it is not used in your application,
at least when it is built with the given configuration.

![Appearing issue in CI-based analysis](img/appearing-issue-CI-analysis.png)

Note also that now you can see the test coverage of the code.
At the moment CI-based or manual analysis is the only way
to display test coverage on SonarCloud or SonarQube.
This is because to gather test coverage, you will need to run the
tests and that is difficult to do without knowing where the tests are and how
they are built.
It is also dangerous because it involves executing unknown code.

![Coverage summary](img/coverage.png)

## 🔍 What you can find in you Sonar report

Sonar reports variaous kinds of findings.
Here is a selection that you can find in this demo project:

### simpler

### issues
### and 
### bugs

### A vulnerability with an execution flow as well as data flows highlighted.

Some particularly deep bugs and vulnerabilities require more context to understand.
Sonar provides this context by offering the data flows for values relevant to an issue.
To see an example you will need to set up [CI-based analysis](#-ci-based-analysis-on-sonarcloud-with-a-coverage-display)
(this issue is not detected in automatic analysis).

Once your code is analyzed, navigate to the "Issues" tab, and select "Vulnerability" and "Blocker" filters.
You should see a vulnerability detected by [S5782](https://rules.sonarsource.com/cpp/RSPEC-5782/).
Alternatively, you can search for "S5782" in the "Rule" filter in the "Issues" tab.

![An issue report with multiple flows](img/multiflow-issue.png)

Clicking on the issue for a detailed view, you'll notice multiple accordeons on the left side:
* Data flow for the size argument that overflows the buffer
* Data flow for the buffer argument
* Execution flow

As you can see, the execution flow in this case is not very informative,
but the data flows allow you to track where the incorrect values of
a memory buffer and a read length come from.


## 🧹 PR analysis: Clean as You Code

This step requires one of the analysis methods (automatic or CI-based) set-up.

Let us open a pull request:
* Substitute `<your account>` in two places in this url and navigate to it:
  `https://github.com/<your account>/cpp-demo/compare/main...<your account>:cpp-demo:add-feature`
* Click on "Create pull request" twice.
* Wait until the analysis finishes
  (the yellow circle 🟡 next to the commit hash should appear
  and turn into a red cross ❌ because quality gate fails).

After a couple of minutes you will see a quality-gate message in your pull request.

![Quality Gate failed](img/qg-failed.png)

Clicking on a link in the message will bring you to the detailed quality-gate view.
Here you can see much fewer findings.
These are findings relevant only to your pull request:
- the new issues or vulnerabilities that you created.
- the pre-existing issues or vulnerabilities in the code that you have modified.

These few issues and vulnerabilities do not take too long to review and fix.
That is the cracks of the Clean as You Code approach:
Clean only the code that you write or modify.
Do not try to fix all the problems in the project.

## ⚡ SonarLint: Fix issues before they exist

Alongside the CI based analysis, SonarLint allows the detection of most issues directly in the IDE.
This allows fixing most issues even before they reach the CI check.

Supported IDEs:
 - Visual Studio
 - Visual Studio Code - shown in the demo
 - CLion - shown in the demo
 - Eclipse

### ⌨ Visual Studio Code
Sonarlint can be acquired from the extension marketplace

![VSCode-Marketplace](img/SL/VSCode-marketplace.png)

SonarLint for VSCode uses a generated `compile_commands.json` to detect the options used to compile the sources. 
Initially, this will not be set.
Once installed, upon having an open C/C++ file, the following notification will appear

![VSCode-compile-commands.png](img/SL/VSCode-compile-commands.png)

By pressing 'Configure compile commands', if the project already has a `compile_commands.json` present in the project's directory structure, it will automatically select that one. If multiple such files exist, you will be prompted to select one of them.

If none exist, you will be linked to a guide to generate this file

![VSCode-compile-commands-missing.png](img/SL/VSCode-compile-commands-missing.png)

The path to the `compile_commands.json` can also be set manually inside `.vscode/settings.json`
```json
{
    "sonarlint.pathToCompileCommands": "path/to/compile_commands.json"
}
```


Once this is set up, issues raised by SonarLint should appear inside your Problems view

![VSCode-issues.png](img/SL/VSCode-issues.png)

Issues will also highlight the code that raises the issue, and can be viewed by hovering over the selection

![VSCode-highlight.png](img/SL/VSCode-highlight.png)


### 🦭 CLion

### 📄 Show rule description

### 🪛 Quick Fix

### 🔌 Synchronize issues between SonarCloud and SonarLint

# 🛬 Teardown 

To prepare for the next demo, you should delete the project from SonarCloud:

* Open the demo-cpp project.
* Click on ⚙ "Administration" in the bottom-left corner, and select "Deletion".
* click on "Delete" and confirm it by entering your project name.

You might also want to delete it from your GitHub account
Click the button at the bottom of the ⚙ "Settings": `https://github.com/<your-account>/cpp-demo/settings`
